// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"whistle_qilin"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是星辰的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "citizen");
        set("owner_name", "星辰");
        set_temp("owner", "citizen");
        set_temp("owner_name", "星辰");
        ::setup();
}
