#!/bin/bash

set -ex

out/host_debug_unopt/ftl_unittests
out/host_debug_unopt/synchronization_unittests
out/host_debug_unopt/wtf_unittests

pushd flutter/testing/dart
pub get
popd

# Verify that a failing test returns a failure code.
! out/host_debug_unopt/sky_shell --disable-observatory --disable-diagnostic --non-interactive --enable-checked-mode --packages=flutter/testing/dart/.packages flutter/testing/fail_test.dart

for TEST_SCRIPT in flutter/testing/dart/*.dart; do
    out/host_debug_unopt/sky_shell --disable-observatory --disable-diagnostic --non-interactive --enable-checked-mode $TEST_SCRIPT
done
