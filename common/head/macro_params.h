//  macro_params.hpp
//
//  Copyright (c) 2003 Eugene Gladyshev
//
//  Permission to copy, use, modify, sell and distribute this software
//  is granted provided this copyright notice appears in all copies.
//  This software is provided "as is" without express or implied
//  warranty, and with no claim as to its suitability for any purpose.
//
#include <map>

#ifndef __ttl_macro_params__hpp
#define __ttl_macro_params__hpp

#include "macro_repeat.h"


#define TTL_TPARAM(n,t) typename t##n, 
#define TTL_TPARAM_END(n,t) typename t##n
#define TTL_TPARAM_DEF(n, def) typename T##n = def, 
#define TTL_TPARAM_DEF_END(n, def) typename T##n = def

#define TTL_TPARAMSX(n,t) TTL_REPEAT(n, TTL_TPARAM, TTL_TPARAM_END, t)
#define TTL_TPARAMS(n) TTL_TPARAMSX(n,T)
#define TTL_TPARAMS_DEF(n, def) TTL_REPEAT(n, TTL_TPARAM_DEF, TTL_TPARAM_DEF_END, def)


#define TTL_ARG(n,t) t##n, 
#define TTL_ARG_END(n,t) t##n
#define TTL_ARG_S(n,t) TTL_APPEND(t, TTL_CNTINC_##n),
#define TTL_ARG_S_END(n,t) TTL_APPEND(t, TTL_CNTINC_##n)

#define TTL_ARGS_DEF(n) TTL_REPEAT(n, TTL_ARG, TTL_ARG_END, t)
#define TTL_ARGSX_DEF(n,t) TTL_REPEAT(n, TTL_ARG, TTL_ARG_END, t)
#define TTL_ARGS_S_DEF(n) TTL_REPEAT(n, TTL_ARG_S, TTL_ARG_S_END, t)
#define TTL_ARGS_SX_DEF(n,t) TTL_REPEAT(n, TTL_ARG_S, TTL_ARG_S_END, t)

#define STD_FORWARD_ARG_T(n, t) std::forward<T##n>(t##n),
#define STD_FORWARD_ARG_END_T(n, t) std::forward<T##n>(t##n)
#define STD_FORWARD_ARG_T_DEF( n ) TTL_REPEAT( n, STD_FORWARD_ARG_T, STD_FORWARD_ARG_END_T, t) 

#define TTL_TYPEDEF(n, t) typedef t##n type##n;
#define TTL_TYPEDEF_END(n, t) typedef t##n type##n;
#define TTL_TYPEDEFS(n) TTL_REPEAT(n, TTL_TYPEDEF, TTL_TYPEDEF_END, T)

#define TTL_LIST_ITEM(n, t) t,
#define TTL_LIST_ITEM_END(n, t) t
#define TTL_LIST_ITEMS(n, t) TTL_REPEAT(n,TTL_LIST_ITEM,TTL_LIST_ITEM_END,t)

#define TTL_FUNC_PARAM(n,t) T##n t##n, 
#define TTL_FUNC_PARAM_END(n,t) T##n t##n
#define TTL_FUNC_PARAMS_T_DEF(n) TTL_REPEAT(n, TTL_FUNC_PARAM, TTL_FUNC_PARAM_END, t)

#define TTL_FUNC_PPARAM(n,t) P##n t##n, 
#define TTL_FUNC_PPARAM_END(n,t) P##n t##n
#define TTL_FUNC_PPARAMS(n, p) TTL_REPEAT(n, TTL_FUNC_PPARAM, TTL_FUNC_PPARAM_END, p)

#define TTL_ENUM_ITEMS(n, t) TTL_REPEAT(n,TTL_ARG,TTL_ARG_END,t)


#define FUSTION_PARI_PARAMS_DEF(n, T) std::pair<K##n, T##n>,
#define FUSTION_PARI_PARAMS_END(n, T) std::pair<K##n, T##n>
#define FUSTION_PARI_PARAMS( n ) TTL_REPEAT( n, FUSTION_PARI_PARAMS_DEF, FUSTION_PARI_PARAMS_END, T) 



#endif //__macro_params__hpp
