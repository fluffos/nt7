// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("夭鹅子水麒麟[2;37;0m[2;37;0m", ({"yaoeziqilin"}));        
        set("gender", "女性");                
        set("long", "夭鹅子水麒麟[2;37;0m
它是夭鹅儿的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "yaoezi");
        set("owner_name", "夭鹅儿");
        set_temp("owner", "yaoezi");
        set_temp("owner_name", "夭鹅儿");
        ::setup();
}
