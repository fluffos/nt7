// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m本体[1;31m短呜[2;37;0m[2;37;0m", ({"wwdd"}));        
        set("gender", "男性");                
        set("long", "短啊短[2;37;0m
它是短呜呜的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wwd");
        set("owner_name", "短呜呜");
        set_temp("owner", "wwd");
        set_temp("owner_name", "短呜呜");
        ::setup();
}
