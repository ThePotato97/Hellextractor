// Copyright 2024 Michael Fabian 'Xaymar' Dirks <info@xaymar.com>
//
// Redistribution and use in source and binary forms, with or without modification, are permitted provided that the following conditions are met:
//
// 1. Redistributions of source code must retain the above copyright notice, this list of conditions and the following disclaimer.
// 2. Redistributions in binary form must reproduce the above copyright notice, this list of conditions and the following disclaimer in the documentation and/or other materials provided with the distribution.
// 3. Neither the name of the copyright holder nor the names of its contributors may be used to endorse or promote products derived from this software without specific prior written permission.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS “AS IS” AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

#include "hd2_wwise_stream.hpp"

helldivers2::wwise_stream::~wwise_stream() {}

helldivers2::wwise_stream::wwise_stream(helldivers2::data::meta_t meta) : _meta(meta)
{
	_header  = reinterpret_cast<decltype(_header)>(_meta.main);
	_data    = reinterpret_cast<decltype(_data)>(_meta.stream ? _meta.stream : _meta.gpu);
	_footer  = reinterpret_cast<decltype(_footer)>(reinterpret_cast<uint8_t const*>(_data) + _header->offset - _meta.main_size);
	_data_sz = (_meta.stream_size ? _meta.stream_size : _meta.gpu_size) - sizeof(footer_t);
}

size_t helldivers2::wwise_stream::size()
{
	return _data_sz;
}

std::string helldivers2::wwise_stream::extension()
{
	return "wem";
}

std::list<std::pair<void const*, size_t>> helldivers2::wwise_stream::sections()
{
	return {
		{_data, _data_sz},
	};
}