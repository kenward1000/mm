/*
 * Copyright (c) 2016-2018 Eric B. Decker
 * All rights reserved.
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 * See COPYING in the top level directory of this source tree.
 *
 * Contact: Eric B. Decker <cire831@gmail.com>
 */

configuration HplSD0C {
  provides {
    interface SDHardware;
  }
}
implementation {
  components Msp432UsciB3P as UsciP;
  components SD0HardwareP  as SDHWP;
  components Msp432DmaC    as DMAC;

  SDHardware = SDHWP;
  SDHWP.Usci      -> UsciP;
  SDHWP.Interrupt -> UsciP;
  SDHWP.DmaTX     -> DMAC.Dma[6];
  SDHWP.DmaRX     -> DMAC.Dma[7];

  components PanicC, PlatformC;
  SDHWP.Panic    -> PanicC;
  SDHWP.Platform -> PlatformC;

  PlatformC.PeripheralInit -> SDHWP;
  SDHWP.DmaInit            -> DMAC;
}
