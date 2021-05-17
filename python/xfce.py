from gi.repository import GLib
from rasmil.xfce import Xfconf

class XfceLidClose(Xfconf):

    def __init__(self):
        Xfconf.__init__(self)

    def get_ac(self) -> int:
        rc = self.get_property('xfce4-power-manager', '/xfce4-power-manager/lid-action-on-ac')
        return rc.get_int32()

    def get_battery(self) -> int:
        rc = self.get_property(
            'xfce4-power-manager', '/xfce4-power-manager/lid-action-on-battery')
        return rc.get_int32()

    def get_suspend(self) -> bool:
        return self.get_ac() == 1

    def set_suspend(self, state: bool):
        if state:
            self.set_property(
                'xfce4-power-manager', '/xfce4-power-manager/lid-action-on-ac', GLib.Variant('i', 1))
            self.set_property(
                'xfce4-power-manager', '/xfce4-power-manager/lid-action-on-battery', GLib.Variant('i', 1))
        else:
            self.set_property(
                'xfce4-power-manager', '/xfce4-power-manager/lid-action-on-ac', GLib.Variant('i', 3))
            self.set_property(
                'xfce4-power-manager', '/xfce4-power-manager/lid-action-on-battery', GLib.Variant('i', 3))


if __name__ == "__main__":
    lid_close = XfceLidClose()
    if lid_close.get_suspend():
        print("Suspend on")
        lid_close.set_suspend(False)
    else:
        print("Suspend off")
        lid_close.set_suspend(True)

    print(f'on ac      : {lid_close.get_ac()}')
    print(f'on battery : {lid_close.get_battery()}')
    