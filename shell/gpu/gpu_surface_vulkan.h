// Copyright 2016 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef SHELL_GPU_GPU_SURFACE_VULKAN_H_
#define SHELL_GPU_GPU_SURFACE_VULKAN_H_

#include <memory>
#include "flutter/shell/common/surface.h"
#include "flutter/vulkan/vulkan_native_surface.h"
#include "flutter/vulkan/vulkan_window.h"
#include "lib/ftl/macros.h"
#include "lib/ftl/memory/weak_ptr.h"

namespace shell {

class GPUSurfaceVulkan : public Surface {
 public:
  GPUSurfaceVulkan(ftl::RefPtr<vulkan::VulkanProcTable> proc_table,
                   std::unique_ptr<vulkan::VulkanNativeSurface> native_surface);

  ~GPUSurfaceVulkan() override;

  bool Setup() override;

  bool IsValid() override;

  std::unique_ptr<SurfaceFrame> AcquireFrame(const SkISize& size) override;

  GrContext* GetContext() override;

 private:
  vulkan::VulkanWindow window_;
  ftl::WeakPtrFactory<GPUSurfaceVulkan> weak_factory_;

  FTL_DISALLOW_COPY_AND_ASSIGN(GPUSurfaceVulkan);
};

}  // namespace shell

#endif  // SHELL_GPU_GPU_SURFACE_VULKAN_H_
