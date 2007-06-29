--[[

   Copyright (C) 2007 MySQL AB

   This program is free software; you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation; version 2 of the License.

   This program is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.

   You should have received a copy of the GNU General Public License
   along with this program; if not, write to the Free Software
   Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA

--]]

-- we need at least 0.5.1
assert(proxy.PROXY_VERSION >= 0x00502, "you need at least mysql-proxy 0.5.1 to run this module")

---
-- read_query() gets the client query before it reaches the server
--
-- @param packet the mysql-packet sent by client
--
-- we have several constants defined, e.g.:
-- * _VERSION
--
-- * proxy.PROXY_VERSION
-- * proxy.COM_* 
-- * proxy.MYSQL_FIELD_*
--
function read_query( packet )
	if packet:byte() == proxy.COM_QUERY then
		print("get got a Query: " .. packet:sub(2))

		-- proxy.PROXY_VERSION is the proxy version as HEX number
		-- 0x00501 is 0.5.1 
		print("we are: " .. string.format("%05x", proxy.PROXY_VERSION))
		print("lua is: " .. _VERSION)
	end
end
