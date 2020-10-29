// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;36m血鸟[2;37;0m[2;37;0m", ({"aiyuwdzq"}));        
        set("gender", "男性");                
        set("long", "浑身是血的小鸟，一看就是常被人欺负的样子……[2;37;0m
它是爱心绝情的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "aiyuwd");
        set("owner_name", "爱心绝情");
        set_temp("owner", "aiyuwd");
        set_temp("owner_name", "爱心绝情");
        ::setup();
}
