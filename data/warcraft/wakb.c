// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"xiaoq"}));        
        set("gender", "女性");                
        set("long", "火麒麟[2;37;0m
它是寂寞的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "wakb");
        set("owner_name", "寂寞");
        set_temp("owner", "wakb");
        set_temp("owner_name", "寂寞");
        ::setup();
}
