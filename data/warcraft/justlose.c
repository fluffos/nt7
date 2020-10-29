// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m玉麒麟[2;37;0m[2;37;0m", ({"qiankun"}));        
        set("gender", "女性");                
        set("long", "不告诉你[2;37;0m
它是晓月的魔幻兽。
");
        set("race_type", "麒麟");
        set("magic/type", "earth");
        set("owner", "justlose");
        set("owner_name", "晓月");
        set_temp("owner", "justlose");
        set_temp("owner_name", "晓月");
        ::setup();
}
