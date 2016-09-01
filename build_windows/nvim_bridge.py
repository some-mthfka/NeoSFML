"""Bridge for connecting a UI instance to nvim."""
import sys
from threading import Semaphore, Thread
from traceback import format_exc

class UIBridge(object):

    """UIBridge class. Connects a Nvim instance to a UI class."""

    def connect(self, nvim, ui):
        """Connect nvim and the ui.

        This will start loops for handling the UI and nvim events while
        also synchronizing both.
        """
        self._error = None
        self._nvim = nvim
        self._ui = ui

        self._nvim_event_loop()

        if self._error:
            print(self._error)

    def exit(self):
        """Disconnect by exiting nvim."""
        self.detach()
        self._call(self._nvim.quit)

    def input(self, input_str):
        """Send input to nvim."""
        self._call(self._nvim.input, input_str)

    def resize(self, columns, rows):
        """Send a resize request to nvim."""
        self._call(self._nvim.ui_try_resize, columns, rows)

    def attach(self, columns, rows, rgb):
        """Attach the UI to nvim."""
        self._call(self._nvim.ui_attach, columns, rows, rgb)

    def detach(self):
        """Detach the UI from nvim."""
        self._call(self._nvim.ui_detach)

    def _call(self, fn, *args):
        self._nvim.async_call(fn, *args)

    def _nvim_event_loop(self):
        def on_setup():
            #print("ON SETUP")
            import messages_from_ui
            file_to_edit = messages_from_ui.get_command_line_argument()
            if file_to_edit != None and file_to_edit != "":
                #in case there is a swap file, command_input will error out
                #and the program won't work
                #use input instead
                #out = self._nvim.command_output("edit " + file_to_edit)
                self._nvim.input("<esc>:edit " + file_to_edit + "<cr>")
                #print("out = ", out)

            self._ui.start(self)

            #print("ON SETUP EXIT")

        def on_request(method, args):
            raise Exception('Not implemented')

        def on_notification(method, updates):
            #print("NOTIFICATIONS")
            def apply_updates():
                try:
                    for update in updates:
                        try:
                            handler = getattr(self._ui, '_nvim_' + update[0])
                            #print('_nvim_' + update[0])
                        except AttributeError:
                            pass
                        else:
                            #for args in update[1:]:
                                #print(*args, end = " ")
                            #print("END")
                            text = ''
                            if update[0] == 'put':
                                for args in update[1:]:
                                    text += str(args)[2]

                                handler(text)
                            else:
                                for args in update[1:]:
                                    handler(*args)
                except:
                    self._error = format_exc()
                    self._call(self._nvim.quit)

            if method == 'redraw':
                if len(updates) > 0:
                    self._ui._nvim_lock_update_mutex();
                    apply_updates();
                    self._ui._nvim_redraw();
                    self._ui._nvim_unlock_update_mutex();

        #print("calling nvim run loop")
        self._nvim.run_loop(on_request, on_notification, on_setup)
        self._ui.quit() #end definition of nvim event loop
