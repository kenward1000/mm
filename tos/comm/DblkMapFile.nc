/**
 *<p>
 * This is a generic interface used by the Tagnet stack to access
 * native C data types.  All of the network specific details are handled
 * by the stack, including conversion from a Native C format to the
 * network internal compact tlv format. The types of adapters supported
 *  is defined by the Tagnet TLV types.
 *</p>
 *
 * @author Daniel J. Maltbie <dmaltbie@daloma.org>
 *
 * @Copyright (c) 2017 Daniel J. Maltbie
 * All rights reserved.
 */
/*
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

#include <Tagnet.h>

interface DblkMapFile
{
  /**
   * returns a pointer to the buffer holding file contents referenced
   * by the current file position. The number of accessible bytes
   * is also returned.
   *
   * 'buf' returns a pointer to a pointer of the byte array within
   * the sector buffer. On entry, 'len' specifies number of bytes
   * desired and on return specifies number of bytes avaialable.
   * If 'len' value is zero on return then requester should try again.
   * This occurs when underlying storage sector buffers are being
   * updated from SD.
   *
   * Because of limited RAM buffering for SD sectors, only a
   * limited  portion of the file can be directly accessed. The
   * file pointer is backed by an underlying sector buffer that
   * is updated when the file position is changed outside of the
   * current sector buffer's file address range.
   *
   * Overall, the amount of data copies is kept to a minimum:
   * (1) sector buffer for holding data from SD, (2) message buffer
   * for network response.
   *
   * The caller must copy data before it performs the next map file
   * interface function or risk buffer pointer becoming invalid.
   *
   * @param   'uint8_t   fd'   file number to access
   * @param   'uint8_t   **buf' pointer to buf pointer
   * @param   'uint32_t  *len' pointer to length available/used
   * @return  'error_t'        error code
   */
  command error_t map(uint8_t fd, uint8_t **buf, uint32_t *len);
  /**
   * move file position of specific dblk file
   *
   * @param   'uint8_t    fd'  file number to access
   * @param   'uint32_t  pos'  new file position requested
   * @param   'bool from_rear' seek from rear (else absolute)
   * @return  'error_t'        error code
   */
  command error_t seek(uint8_t fd, uint32_t pos, bool from_rear);
  /**
   * return current file position of specific dblk file
   *
   * @param   'uint8_t   fd'   file number to access
   * @return  'uint32_t'       current file position
   */
  command uint32_t tell(uint8_t fd);
  /**
   * signal when a new sector has been written to
   * specific dblk file
   *
   * @param   'uint8_t   fd'   file number to access
   * @param   'uint32_t file_pos' new file memory mapped
   */
  event void mapped(uint8_t fd, uint32_t file_pos);
  /**
   * return size of file in bytes
   *
   * @param   'uint8_t   fd'   file number to access
   * @return  'uint32_t'       file size in bytes
   */
  command uint32_t filesize(uint8_t fd);
}
