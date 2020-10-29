// This program is a part of NITAN MudLIB 
// redl 2015/4

#include <ansi.h>
#include "medicine.h"

void create()
{
        set_name(HIR "火枣" NOR, ({"huo zao", "zao"}));
                set("long", "这是一粒血脉丹，可激活体内血脉能力。\n");
                set("base_unit", "颗");

                set("base_value", 5000000);
                set("base_weight", 80);
                set("only_do_effect", 1);
                set("mixture", ([
                        "herb" : ([ "/clone/fam/pill/linghui1"   : 3,
//                                    "blood"   : 1,
  //                                  "xuelian2": 1,
    //                                "yulu"    : 1,
      //                              "sheli4"  : 1,
        //                            "renshen2": 1,
          //                          "puti4"   : 1,
            //                        "lingzhi2": 1,
              //                      "dimai"   : 1 ]),
                                                ]),
                        "neili" : 800,
                        "jing"  : 200,
                        "time"  : 5,
                        "min_level" : 600,
                        "medical" : 1000,
                        "liandan-shu" : 3300,
                ]));
        setup();
}

int do_effect(object me) 
{
        write("血脉丹只能在修炼血脉upblood时候服用。\n"); 
        return 1;
}
