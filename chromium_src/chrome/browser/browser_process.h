// Copyright (c) 2012 The Chromium Authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

// This interface is for managing the global services of the application. Each
// service is lazily created when requested the first time. The service getters
// will return NULL if the service is not available, so callers must check for
// this condition.

#ifndef CHROME_BROWSER_BROWSER_PROCESS_H_
#define CHROME_BROWSER_BROWSER_PROCESS_H_

#include <memory>
#include <string>

#include "base/macros.h"

#if defined(ENABLE_EXTENSIONS)
namespace extensions {
class ExtensionsBrowserClient;
}
namespace component_updater {
class ComponentUpdateService;
}
#endif

namespace printing {
class PrintJobManager;
}

// NOT THREAD SAFE, call only from the main thread.
// These functions shouldn't return NULL unless otherwise noted.
class BrowserProcess {
 public:
  BrowserProcess();
  ~BrowserProcess();

  std::string GetApplicationLocale();

  printing::PrintJobManager* print_job_manager();

  bool IsShuttingDown();
  void StartTearDown();
  component_updater::ComponentUpdateService* component_updater();

 private:
  std::unique_ptr<printing::PrintJobManager> print_job_manager_;
#if defined(ENABLE_EXTENSIONS)
  std::unique_ptr<extensions::ExtensionsBrowserClient> extensions_browser_client_;
#endif
  bool tearing_down_;
  std::unique_ptr<component_updater::ComponentUpdateService> component_updater_;
  DISALLOW_COPY_AND_ASSIGN(BrowserProcess);
};

extern BrowserProcess* g_browser_process;

#endif  // CHROME_BROWSER_BROWSER_PROCESS_H_
