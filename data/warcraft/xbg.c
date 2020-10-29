// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[31m西门吹雪[2;37;0m[2;37;0m", ({"xmcx"}));        
        set("gender", "男性");                
        set("long", "西门吹雪吹的不是雪[2;37;0m
它是韦小宝的魔幻兽。
");
        set("race_type", "青龙");
        set("magic/type", "wood");
        set("owner", "xbg");
        set("owner_name", "韦小宝");
        set_temp("owner", "xbg");
        set_temp("owner_name", "韦小宝");
        ::setup();
}
