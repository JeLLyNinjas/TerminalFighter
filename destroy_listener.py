
"""
    If your class wants to listen to when an object says it is destroyed
    inherit this "interface" and then pass yourself in as an argument to the
    register function
"""


class DestroyListener():

    def reported_destroyed(self, type_gameobject):
        raise NotImplementedError()
