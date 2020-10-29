// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("爱骑[2;37;0m[2;37;0m", ({"ilovelong"}));        
        set("gender", "女性");                
        set("long", "我爱我的龙龙[2;37;0m
它是文瑞燕的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wenruiyan");
        set("owner_name", "文瑞燕");
        set_temp("owner", "wenruiyan");
        set_temp("owner_name", "文瑞燕");
        ::setup();
}
