// Copyright 2017 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#include "flutter/flow/layers/physical_model_layer.h"

#include "third_party/skia/include/utils/SkShadowUtils.h"

namespace flow {

PhysicalModelLayer::PhysicalModelLayer()
    : rrect_(SkRRect::MakeEmpty()) {}

PhysicalModelLayer::~PhysicalModelLayer() {}

void PhysicalModelLayer::Preroll(PrerollContext* context, const SkMatrix& matrix) {
  PrerollChildren(context, matrix);
  if (!context->child_paint_bounds.intersect(rrect_.getBounds()))
    context->child_paint_bounds.setEmpty();

  // Add some margin to the paint bounds to leave space for the shadow.
  // The margin is hardcoded to an arbitrary maximum for now because Skia
  // doesn't provide a way to calculate it.
  SkRect bounds(rrect_.getBounds());
  bounds.outset(50.0, 50.0);
  set_paint_bounds(bounds);
}

void PhysicalModelLayer::Paint(PaintContext& context) {
  TRACE_EVENT0("flutter", "PhysicalModelLayer::Paint");
  // TODO: need to support this layer on Fuchsia
  FTL_DCHECK(!needs_system_composite());

  SkPath path;
  path.addRRect(rrect_);

  if (elevation_ != 0) {
    SkShadowUtils::DrawShadow(&context.canvas, path,
                              elevation_ * 4,
                              SkPoint3::Make(0.0f, -700.0f, 2800.0f),
                              2800.0f,
                              0.25f, 0.25f,
                              SK_ColorBLACK);
  }

  SkPaint paint;
  paint.setColor(SkColorSetA(color_, 0xFF));
  context.canvas.drawPath(path, paint);

  SkAutoCanvasRestore save(&context.canvas, false);
  if (rrect_.isRect()) {
    context.canvas.save();
  } else {
    context.canvas.saveLayer(&rrect_.getBounds(), nullptr);
  }
  context.canvas.clipRRect(rrect_, true);
  PaintChildren(context);
}

}  // namespace flow
