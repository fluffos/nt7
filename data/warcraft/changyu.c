// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("裕张[2;37;0m[2;37;0m", ({"yuchang"}));        
        set("gender", "女性");                
        set("long", "裕张[2;37;0m
它是张裕的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "changyu");
        set("owner_name", "张裕");
        set_temp("owner", "changyu");
        set_temp("owner_name", "张裕");
        ::setup();
}
