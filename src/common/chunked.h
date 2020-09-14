/**
 * This file is part of Hercules.
 * http://herc.ws - http://github.com/HerculesWS/Hercules
 *
 * Copyright (C) 2020 Hercules Dev Team
 * Copyright (C) 2020 Andrei Karas (4144)
 *
 * Hercules is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#ifndef COMMON_CHUNKED_H
#define COMMON_CHUNKED_H

#ifndef WFIFO_CHUNK_SIZE
#define WFIFO_CHUNK_SIZE 65500
#endif  // WFIFO_CHUNK_SIZE

#define WFIFO_CHUNKED_INIT(p, fd, header, pname, data, data_len) \
	struct pname *p = NULL; \
	int p ## _len = 0; \
	int p ## _offset = 0; \
	const int p ## _fd = fd; \
	const int p ## _fixed_len = sizeof(struct pname); \
	const int p ## _header_id = header; \
	const char *p ## data = data; \
	const int p ## data_len = data_len; \
	const int p ## _full_chunks_count = data_len / WFIFO_CHUNK_SIZE; \
	for (int p ## _cnt = 0; p ## _cnt < p ## _full_chunks_count; p ## _cnt ++, p ## _offset += WFIFO_CHUNK_SIZE)

#define WFIFO_CHUNKED_BLOCK_START(p) \
		p ## _len = p ## _fixed_len + WFIFO_CHUNK_SIZE; \
		WFIFOHEAD(p ## _fd, p ## _len); \
		p = WFIFOP(p ## _fd, 0); \
		WFIFOW(p ## _fd, 0) = p ## _header_id; \
		WFIFOW(p ## _fd, 2) = p ## _len; \
		if (p ## _cnt == 0) \
			(p)->flag = 0; \
		else \
			(p)->flag = 1; \
		memcpy((p)->data, p ## data + p ## _offset, WFIFO_CHUNK_SIZE)

#define WFIFO_CHUNKED_BLOCK_END() \
		WFIFOSET(p ## _fd, p ## _len)

#define WFIFO_CHUNKED_START_FINAL(p) \
	const uint32 p ## _left_size = p ## data_len - p ## _full_chunks_count * WFIFO_CHUNK_SIZE; \
	p ## _len = p ## _fixed_len + p ## _left_size; \
	WFIFOHEAD(p ## _fd, p ## _len); \
	p = WFIFOP(p ## _fd, 0); \
	WFIFOW(p ## _fd, 0) = p ## _header_id; \
	WFIFOW(p ## _fd, 2) = p ## _len; \
	(p)->flag = 2; \
	if (p ## _left_size > 0) \
		memcpy((p)->data, p ## data + p ## _offset, p ## _left_size);

#endif /* COMMON_CHUNKED_H */
