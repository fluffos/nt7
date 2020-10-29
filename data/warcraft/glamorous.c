// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;32m靓[1;31m爆[1;35m你[1;36m双眼[2;37;0m[2;37;0m[2;37;0m", ({"blast"}));        
        set("gender", "女性");                
        set("long", "靓爆你双眼![2;37;0m
它是妹纸贼拽的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "glamorous");
        set("owner_name", "妹纸贼拽");
        set_temp("owner", "glamorous");
        set_temp("owner_name", "妹纸贼拽");
        ::setup();
}
