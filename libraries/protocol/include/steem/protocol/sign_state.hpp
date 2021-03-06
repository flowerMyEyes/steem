#pragma once

#include <steem/protocol/authority.hpp>
#include <steem/protocol/types.hpp>

namespace steem { namespace protocol {

typedef std::function<authority(const string&)> authority_getter;

struct sign_state
{
      /** returns true if we have a signature for this key or can
       * produce a signature for this key, else returns false.
       */
      bool signed_by( const public_key_type& k );
      bool check_authority( string id, bool enforce_membership_limit = false );

      /**
       *  Checks to see if we have signatures of the active authorites of
       *  the accounts specified in authority or the keys specified.
       */
      bool check_authority( const authority& au, uint32_t depth = 0, bool enforce_membership_limit = false );
      bool check_authority( const authority& au, bool enforce_membership_limit );

      bool remove_unused_signatures();

      sign_state( const flat_set<public_key_type>& sigs,
                  const authority_getter& a,
                  const flat_set<public_key_type>& keys );

      const authority_getter&          get_active;
      const flat_set<public_key_type>& available_keys;

      flat_map<public_key_type,bool>   provided_signatures;
      flat_set<string>                 approved_by;
      uint32_t                         max_recursion = STEEM_MAX_SIG_CHECK_DEPTH;
};

} } // steem::protocol
