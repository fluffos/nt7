// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[37m小白[2;37;0m[2;37;0m", ({"xiaobai"}));        
        set("gender", "男性");                
        set("long", "一只通体晶莹剔透，白璧无瑕的麒麟。[2;37;0m
它是小天的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "shadowkwan");
        set("owner_name", "小天");
        set_temp("owner", "shadowkwan");
        set_temp("owner_name", "小天");
        ::setup();
}
