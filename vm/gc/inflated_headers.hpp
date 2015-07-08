#include <stddef.h>
#include <list>
#include "diagnostics.hpp"
#include "prelude.hpp"
#include "util/allocator.hpp"

namespace rubinius {
  class ObjectHeader;
  class InflatedHeader;
  class VM;

  class InflatedHeaders {
  public:
    class Diagnostics : public diagnostics::MemoryDiagnostics {
    public:
      int64_t collections_;

      Diagnostics()
        : diagnostics::MemoryDiagnostics()
        , collections_(0)
      { }

      void log();
    };

  private:
    Allocator<InflatedHeader>* allocator_;

    Diagnostics diagnostics_;

  public:
    InflatedHeaders()
      : allocator_(new Allocator<InflatedHeader>())
      , diagnostics_(Diagnostics())
    {}

    ~InflatedHeaders() {
      delete allocator_;
    }

    InflatedHeader* allocate(STATE, ObjectHeader* obj, uint32_t* index);

    InflatedHeader* find_index(uintptr_t index) {
      return allocator_->from_index(index);
    }

    void deallocate_headers(unsigned int mark);

    int size() const {
      return allocator_->in_use_;
    }

    Diagnostics& diagnostics() {
      return diagnostics_;
    }
  };
}
