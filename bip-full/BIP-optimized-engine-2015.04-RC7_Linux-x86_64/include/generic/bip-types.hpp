#ifndef _BIP_Engine_bip_types_HPP_
#define _BIP_Engine_bip_types_HPP_

namespace biptypes {
    enum ComponentType {
        ATOM = 0,
        COMPOUND = 1
    };
    enum ExportType {
        ATOM_EXPORT = 0,
        COMPOUND_EXPORT = 1,
        CONNECTOR_EXPORT = 2
    };
    enum ErrorType {
        NO_ERROR = 0,
        NON_DETERMINISTIC_PETRI_NET = 1,
        NON_ONE_SAFE_PETRI_NET = 2,
        CYCLE_IN_PRIORITIES = 3,
        CYCLE_IN_ATOM_PRIORITIES = 4
    };
}

#endif // _BIP_Engine_bip_types_HPP_
