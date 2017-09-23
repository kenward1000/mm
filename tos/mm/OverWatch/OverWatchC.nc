/**
 * Copyright (c) 2017 Eric B. Decker
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 *
 * - Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 *
 * - Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the
 *   distribution.
 *
 * - Neither the name of the copyright holders nor the names of
 *   its contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
 * "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
 * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
 * FOR A PARTICULAR PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL
 * THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT,
 * INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
 * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 * HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT,
 * STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
 * ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED
 * OF THE POSSIBILITY OF SUCH DAMAGE.
 */

/*
 * @author Eric B. Decker
 *
 * Configuration wiring for OverWatch.  See OverWatchP for more details on
 * what OverWatch does.
 */

#include <overwatch.h>

configuration OverWatchC {
  provides {
    interface Boot as Booted;		/* out Booted signal */
    interface OverWatch as OW;
  }
  uses interface Boot;			/* incoming signal */
}

implementation {
  components OverWatchP as OW_P;
  OW     = OW_P;
  Booted = OW_P;
  Boot   = OW_P;

  components SD0C, SSWriteC;
  OW_P.SSW  -> SSWriteC;
  OW_P.SDsa -> SD0C;

  components ChecksumM;
  components ImageManagerC as IM_C;
  components OverWatchHardwareM;
  OW_P.Checksum -> ChecksumM;
  OW_P.OWhw     -> OverWatchHardwareM;
  OW_P.IM       -> IM_C.IM[unique("image_manager_clients")];
  OW_P.IMD      -> IM_C;

  components PlatformC;
  OW_P.SysReboot -> PlatformC;
  OW_P.Platform  -> PlatformC;
}
