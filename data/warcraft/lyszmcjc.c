// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m朱雀[2;37;0m[2;37;0m", ({"lyz"}));        
        set("gender", "女性");                
        set("long", "恒久远[2;37;0m
它是小恒恒的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "lyszmcjc");
        set("owner_name", "小恒恒");
        set_temp("owner", "lyszmcjc");
        set_temp("owner_name", "小恒恒");
        ::setup();
}
