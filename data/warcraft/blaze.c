// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[5m[1;31m火气[1;32m腾[1;35m腾[2;37;0m[2;37;0m[2;37;0m", ({"blazing"}));        
        set("gender", "男性");                
        set("long", "火气腾腾！[2;37;0m
它是火炎焱的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "blaze");
        set("owner_name", "火炎焱");
        set_temp("owner", "blaze");
        set_temp("owner_name", "火炎焱");
        ::setup();
}
