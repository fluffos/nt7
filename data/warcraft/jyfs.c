// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("火麒麟[2;37;0m[2;37;0m", ({"qilin"}));        
        set("gender", "女性");                
        set("long", "火麒麟[2;37;0m
它是轩辕枫的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "jyfs");
        set("owner_name", "轩辕枫");
        set_temp("owner", "jyfs");
        set_temp("owner_name", "轩辕枫");
        ::setup();
}
