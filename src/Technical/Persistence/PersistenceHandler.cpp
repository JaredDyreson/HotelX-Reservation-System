#include "../../../include/Technical/Persistence/PersistenceHandler.hpp"
#include "../../../include/Technical/Persistence/SimpleDB.hpp"
#include "../../../include/Technical/Persistence/ExtraSimple.hpp"

namespace Technical::Persistence
{
  PersistenceHandler::~PersistenceHandler() noexcept = default;




  PersistenceHandler & PersistenceHandler::instance()
  {
    // Can't read the DB component preference from the database because the DB has not yet been created. So choosing the database
    // implementation is really a configuration item (set by the vendor before delivery), not an adaptable item (set by the end-user
    // after delivery)
     using SelectedDatabase = SimpleDB;

     static SelectedDatabase instance;    // Note the creation of a DB specialization (derived class), but returning a reference to
                                         // the generalization (base class). Since SimpleDB is-a PersistenceHandler, we can return a
                                         // reference to the base class that refers to a specific derived class.  SimpleDB is
                                         // accessed polymorphicly through the PersistenceHandler interface.  This source file knows
                                         // about the specific SimpleDB derived class, but that's okay.  This source file is not
                                         // delivered with the interface and remains That is, PersistenceHandler.hpp is given to the
                                         // upper architectural layers, but not PersistenceHandler.cpp.
    
    auto & persistantData = Technical::Persistence::PersistenceHandler::instance();
    auto   requesedUI     = persistantData["Component.DB"];

    std::cout << "selected database is " << requesedUI << std::endl;

    //if     ( requesedUI == "Simple DB"     ) return std::make_unique<Technical::Persistence::SimpleDB>      ();
    //else if( requesedUI == "Extra Simple DB" ) return std::make_unique<Technical::Persistence::ExtraSimpleDB>();

    return instance;
  }

  std::unique_ptr<PersistenceHandler> PersistenceHandler::createDatabase() {
      return std::unique_ptr<Technical::Persistence::SimpleDB>();
  }
}    // namespace Technical::Persistence
