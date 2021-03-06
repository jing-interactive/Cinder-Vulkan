/*
 Copyright 2016 Google Inc.
 
 Licensed under the Apache License, Version 2.0 (the "License");
 you may not use this file except in compliance with the License.
 You may obtain a copy of the License at
 
 http://www.apache.org/licenses/LICENSE-2.0
 
 Unless required by applicable law or agreed to in writing, software
 distributed under the License is distributed on an "AS IS" BASIS,
 WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 See the License for the specific language governing permissions and
 limitations under the License.


 Copyright (c) 2016, The Cinder Project, All rights reserved.

 This code is intended for use with the Cinder C++ library: http://libcinder.org

 Redistribution and use in source and binary forms, with or without modification, are permitted provided that
 the following conditions are met:

    * Redistributions of source code must retain the above copyright notice, this list of conditions and
	the following disclaimer.
    * Redistributions in binary form must reproduce the above copyright notice, this list of conditions and
	the following disclaimer in the documentation and/or other materials provided with the distribution.

 THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND ANY EXPRESS OR IMPLIED
 WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
 PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE FOR
 ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED
 TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
 HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
 NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
 POSSIBILITY OF SUCH DAMAGE.
*/

#pragma once

#include "cinder/vk/Buffer.h"

namespace cinder { namespace vk {

class IndexBuffer;
using IndexBufferRef = std::shared_ptr<IndexBuffer>;

//! \class IndexBuffer
//!
//!
class IndexBuffer : public Buffer {
public:

	class Format : public vk::Buffer::Format {
	public:
		Format( VkMemoryPropertyFlags memoryProperty = VK_MEMORY_PROPERTY_HOST_VISIBLE_BIT )
			: vk::Buffer::Format( VK_BUFFER_USAGE_INDEX_BUFFER_BIT, memoryProperty ) {}
		virtual ~Format() {}

		Format&					setUsageTransferSource() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_TRANSFER_SRC_BIT ); return *this; }
		Format&					setUsageTransferDestination() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_TRANSFER_DST_BIT ); return *this; }
		Format&					setUsageUniformTexelBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_UNIFORM_TEXEL_BUFFER_BIT ); return *this; }
		Format&					setUsageStorageTexelBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_STORAGE_TEXEL_BUFFER_BIT ); return *this; }
		Format&					setUsageUniformBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_UNIFORM_BUFFER_BIT ); return *this; }
		Format&					setUsageStorageBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_STORAGE_BUFFER_BIT ); return *this; }
		Format&					setUsageIndexBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_INDEX_BUFFER_BIT ); return *this; }
		Format&					setUsageVertexBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_VERTEX_BUFFER_BIT ); return *this; }
		Format&					setUsageIndirectBuffer() { vk::Buffer::Format::setUsage( VK_BUFFER_USAGE_INDIRECT_BUFFER_BIT ); return *this; }

		Format&					setTransientAllocation( bool value = true ) { vk::Buffer::Format::setTransientAllocation( value ); return *this; }
	private:
		friend class IndexBuffer;
	};

	// ---------------------------------------------------------------------------------------------

	virtual ~IndexBuffer();

	static IndexBufferRef create( size_t numIndices, VkIndexType indexType, const void *indices, const vk::IndexBuffer::Format& format, vk::Device *device = nullptr );

	VkIndexType					getIndexType() const { return mIndexType; }
	size_t						getNumIndices() const { return mNumIndices; }

	void						bufferIndices( const std::vector<uint16_t> &indices, size_t offset = 0 );
	void						bufferIndices( const std::vector<uint32_t> &indices, size_t offset = 0 );

private:
	IndexBuffer( size_t numIndices, VkIndexType indexType, const void *indices, const vk::IndexBuffer::Format& format, vk::Device *device );

	VkIndexType					mIndexType = VK_INDEX_TYPE_UINT32;
	size_t						mNumIndices = 0;
	
	void initialize( size_t numIndices, VkIndexType indexType, const void *indices );
	void destroy( bool removeFromTracking = true );
	friend class Device;
};

}} // namespace cinder::vk