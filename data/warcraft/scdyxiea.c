// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("白白白白白虎[2;37;0m[2;37;0m", ({"xiea"}));        
        set("gender", "男性");                
        set("long", "一只白老虎[2;37;0m
它是伯赏昆裕的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "scdyxiea");
        set("owner_name", "伯赏昆裕");
        set_temp("owner", "scdyxiea");
        set_temp("owner_name", "伯赏昆裕");
        ::setup();
}
