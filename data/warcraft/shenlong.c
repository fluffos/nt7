// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m龙飞凤舞[2;37;0m[2;37;0m", ({"bailong"}));        
        set("gender", "女性");                
        set("long", "这是一头小白龙。[2;37;0m
它是龙啸天的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "shenlong");
        set("owner_name", "龙啸天");
        set_temp("owner", "shenlong");
        set_temp("owner_name", "龙啸天");
        ::setup();
}
