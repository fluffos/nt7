// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("小飞米[2;37;0m[2;37;0m", ({"xmf"}));        
        set("gender", "女性");                
        set("long", "小飞米[2;37;0m
它是白米饭的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "mifana");
        set("owner_name", "白米饭");
        set_temp("owner", "mifana");
        set_temp("owner_name", "白米饭");
        ::setup();
}
