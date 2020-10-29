// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;35m凤凰[1;37m传奇[2;37;0m[2;37;0m", ({"dalimoone"}));        
        set("gender", "女性");                
        set("long", "这个是什么，你懂的。[2;37;0m
它是大粒墨的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "dalimo");
        set("owner_name", "大粒墨");
        set_temp("owner", "dalimo");
        set_temp("owner_name", "大粒墨");
        ::setup();
}
