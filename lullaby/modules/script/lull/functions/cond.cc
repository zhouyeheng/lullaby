/*
Copyright 2017 Google Inc. All Rights Reserved.

Licensed under the Apache License, Version 2.0 (the "License");
you may not use this file except in compliance with the License.
You may obtain a copy of the License at

    http://www.apache.org/licenses/LICENSE-2.0

Unless required by applicable law or agreed to in writing, software
distributed under the License is distributed on an "AS-IS" BASIS,
WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
See the License for the specific language governing permissions and
limitations under the License.
*/

#include "lullaby/modules/script/lull/script_env.h"
#include "lullaby/modules/script/lull/script_frame.h"
#include "lullaby/modules/script/lull/script_types.h"

namespace lull {

void Cond(ScriptFrame* frame) {
  ScriptValue value = frame->EvalNext();
  const bool* condition = value.Get<bool>();
  if (condition && *condition) {
    // Evaluate the first path.
    if (frame->HasNext()) {
      frame->Return(frame->EvalNext());
    }
    // Skip the other path.
    if (frame->HasNext()) {
      frame->Next();
    }
  } else {
    // Skip the first path.
    if (frame->HasNext()) {
      frame->Next();
    }
    // Evaluate the second path.
    if (frame->HasNext()) {
      frame->Return(frame->EvalNext());
    }
  }

  if (frame->HasNext()) {
    frame->Error("Condition statement should only have two paths.");
  }
}

}  // namespace lull
