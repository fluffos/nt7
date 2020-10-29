// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m火麒麟[2;37;0m[2;37;0m", ({"hqilin"}));        
        set("gender", "男性");                
        set("long", "火麒麟[2;37;0m
它是天上星的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "dutian");
        set("owner_name", "天上星");
        set_temp("owner", "dutian");
        set_temp("owner_name", "天上星");
        ::setup();
}
