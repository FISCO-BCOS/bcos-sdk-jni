/*
 * Copyright 2014 The Netty Project
 *
 * The Netty Project licenses this file to you under the Apache License,
 * version 2.0 (the "License"); you may not use this file except in compliance
 * with the License. You may obtain a copy of the License at:
 *
 *   https://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS, WITHOUT
 * WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied. See the
 * License for the specific language governing permissions and limitations
 * under the License.
 */
package org.fisco.bcos.sdk.jni.common;

import java.io.File;

/** Helper class to load JNI resources. */
public final class NativeLibraryLoader {

  private static final String NATIVE_RESOURCE_HOME = "META-INF/native/";
  // private static final File WORKDIR;

  static {
    String workdir = System.getProperty("fisco.bcos.native.workdir");
    if (workdir != null) {
      File f = new File(workdir);
      f.mkdirs();

      try {
        f = f.getAbsoluteFile();
      } catch (Exception ignored) {
        // Good to have an absolute path, but it's OK.
      }

      // WORKDIR = f;
    } else {
      // WORKDIR = PlatformDependent.tmpdir();
    }
  }

  /**
   * Delegate the calling to {@link System#load(String)} or {@link System#loadLibrary(String)}.
   *
   * @param libName - The native library path or name
   * @param absolute - Whether the native library will be loaded by path or by name
   */
  public static void loadLibrary(String libName, boolean absolute) {
    if (absolute) {
      System.load(libName);
    } else {
      System.loadLibrary(libName);
    }

    // System.loadLibrary("fisco-cpp-sdk");
  }
}
