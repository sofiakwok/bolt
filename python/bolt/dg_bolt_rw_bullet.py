"""

License: BSD 3-Clause License
Copyright (C) 2018-2021, New York University , Max Planck Gesellschaft
Copyright note valid unless otherwise stated in individual files.
All rights reserved.
"""

from robot_properties_bolt.config import BoltRWConfig
from bolt.dg_bolt_rw_base_bullet import DgBoltRWBaseRobot


class BoltRWBulletRobot(DgBoltRWBaseRobot):
    def __init__(
        self,
        use_fixed_base=False,
    ):
        super(BoltRWBulletRobot, self).__init__(
            BoltRWConfig(),
            use_fixed_base=use_fixed_base,
        )

        self.q0[2] = 0.26487417
        # self.q0[5] = -0.1736482
        self.q0[6] = 1.0
        self.q0[7] = 0.0
        self.q0[8] = 0.78539816
        self.q0[9] = -1.57079633
        self.q0[10] = 0.0
        self.q0[11] = 0.78539816
        self.q0[12] = -1.57079633
        self.q0[13] = 0.0

        # Sync the current robot state to the graph input signals.
        self._sim2signal()


def get_bolt_robot(use_fixed_base=False):
    return BoltRWBulletRobot(use_fixed_base)
