// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m神[31m马[1;32m不[34m是[1;33m白[35m云[2;37;0m[2;37;0m", ({"ouyangfeng"}));        
        set("gender", "男性");                
        set("long", "什么号召[2;37;0m
它是剑锋的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "btab");
        set("owner_name", "剑锋");
        set_temp("owner", "btab");
        set_temp("owner_name", "剑锋");
        ::setup();
}
