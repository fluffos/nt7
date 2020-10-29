// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;31m红玫瑰[2;37;0m[2;37;0m", ({"redcake"}));        
        set("gender", "女性");                
        set("long", "红色玫瑰[2;37;0m
它是飘雪掌的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "ljjem");
        set("owner_name", "飘雪掌");
        set_temp("owner", "ljjem");
        set_temp("owner_name", "飘雪掌");
        ::setup();
}
