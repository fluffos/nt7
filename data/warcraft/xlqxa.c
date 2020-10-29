// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;36m青色垃圾龙[2;37;0m[2;37;0m", ({"xlqxaa"}));        
        set("gender", "女性");                
        set("long", "都是很丑[2;37;0m
它是路飞的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xlqxa");
        set("owner_name", "路飞");
        set_temp("owner", "xlqxa");
        set_temp("owner_name", "路飞");
        ::setup();
}
