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
import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.InputStream;
import java.nio.file.Files;
import java.nio.file.StandardCopyOption;
import org.slf4j.Logger;
import org.slf4j.LoggerFactory;

/**
 * Helper class to load fisco bcos jni resources.
 *
 * @author octopus
 */
public final class JniLibLoader {
  private static final Logger logger = LoggerFactory.getLogger(JniLibLoader.class);

  public static final String LINUX = "linux";
  public static final String MAC = "mac";
  public static final String WIN = "win";

  public static final String NATIVE_RESOURCE_LIB_NAME = "bcos-sdk-jni";
  public static final String NATIVE_RESOURCE_HOME = "/META-INF/native";

  public static final String OS_NAME = getOs();
  public static final String ARCH_NAME = getArch();

  private static File WORKDIR;

  static {
    // 1. initialize workdir

    // -Dorg.fisco.bcos.workdir
    String workdir = System.getProperty("org.fisco.bcos.workdir");
    if (workdir != null) {
      try {
        File f = new File(workdir);
        f.mkdirs();
        WORKDIR = f;
        logger.info("initialize workdir, -Dorg.fisco.bcos.workdir: {}", WORKDIR);
      } catch (Exception e) {
        logger.debug("initialize workdir, cannot mkdir workdir: {}, e: ", workdir, e);
        workdir = null;
      }
    }

    // default -Djava.io.tmpdir
    if (workdir == null) {
      workdir = System.getProperty("java.io.tmpdir");
      File f = new File(workdir);
      f.mkdirs();
      WORKDIR = f;

      logger.info("initialize workdir, -Djava.io.tmpdirs: {}", WORKDIR);
    }
  }

  public static String getArch() {
    String archName = System.getProperty("os.arch", "");
    if (archName.contains("aarch64")) {
      return "arm";
    } else {
      return "";
    }
  }

  public static String getLibName(String libName) {
    String osName = OS_NAME;
    String archName = ARCH_NAME;

    if (logger.isTraceEnabled()) {
      logger.trace("osName: {}, archName: {}", osName, archName);
    }

    if (osName.contains(WIN)) {
      return "lib" + libName + ".dll";
    } else if (osName.contains(LINUX)) {
      return "lib" + libName + ".so";
    } else if (osName.contains(MAC)) {
      return "lib" + libName + ".dylib";
    } else {
      throw new RuntimeException("unrecognized OS: " + osName);
    }
  }

  public static String getOs() {
    String osName = System.getProperty("os.name").toLowerCase();
    if (osName.contains(WIN)) {
      return WIN;
    } else if (osName.contains(LINUX)) {
      return LINUX;
    } else if (osName.contains(MAC)) {
      return MAC;
    } else {
      throw new RuntimeException("unrecognized OS: " + osName);
    }
  }

  public static void loadJniLibrary() {
    String libPath = null;
    boolean loadLibFromFsOk = false;
    try {
      // 1. try to load library from filesystem
      //  -Dorg.fisco.bcos.jni.library.path
      libPath = System.getProperty("org.fisco.bcos.jni.library.path");
      if (libPath != null) {
        logger.info("try to load library -Dorg.fisco.bcos.jni.library.path, libPath: {}", libPath);
        // try to load library from filesystem first
        loadLibraryFromFs(libPath, NATIVE_RESOURCE_LIB_NAME, new File(libPath).isAbsolute());
        loadLibFromFsOk = true;
      }
    } catch (Exception e0) {
      logger.error("unable to load library from fs, libDir: {}, e: ", libPath, e0);
    }

    // 2. try to load library from jar
    if (!loadLibFromFsOk) {
      try {
        logger.info("try to load library from jar");
        loadLibraryFromJar(NATIVE_RESOURCE_LIB_NAME);
      } catch (Exception e1) {
        logger.error("unable to load library from fs, e: ", e1);
        throw new UnsatisfiedLinkError(e1.toString());
      }
    }
  }

  public static void loadLibrary(String lib, boolean absolute) {
    if (absolute) {
      System.load(lib);
    } else {
      System.loadLibrary(lib);
    }
  }

  public static void loadLibraryFromFs(String dir, String libName, boolean absolute) {
    String resource = dir + "/" + getLibName(libName);
    loadLibrary(resource, absolute);
  }

  public static void loadLibraryFromJar(String libName) throws IOException {
    long suffix = System.nanoTime();
    String tempPath = libName + "_" + suffix;
    File tempFilePath = new File(WORKDIR, tempPath);

    if (logger.isDebugEnabled()) {
      logger.debug("tempPath: {}", tempPath);
    }

    String resource = NATIVE_RESOURCE_HOME + "/" + getLibName(libName);
    try (InputStream is = JniLibLoader.class.getResourceAsStream(resource)) {
      Files.copy(is, tempFilePath.toPath(), StandardCopyOption.REPLACE_EXISTING);
    } catch (IOException e) {
      try {
        tempFilePath.delete();
      } catch (Exception e0) {
        logger.debug("delete temp file error, e: ", e0);
      }
      throw e;
    } catch (NullPointerException e) {
      throw new FileNotFoundException("Cannot found " + resource + " inside the JAR.");
    }
    try {
      loadLibrary(tempFilePath.getAbsolutePath(), true);
    } finally {
      tempFilePath.deleteOnExit();
    }
  }
}
