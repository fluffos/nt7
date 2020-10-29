// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[43;1m[34m猪鸟[2;37;0m[2;37;0m", ({"zque"}));        
        set("gender", "女性");                
        set("long", "$HBYEL$$BLU$猪鸟[2;37;0m
它是唐花的魔幻兽。
");
        set("race_type", "朱雀");
        set("magic/type", "fire");
        set("owner", "wuca");
        set("owner_name", "唐花");
        set_temp("owner", "wuca");
        set_temp("owner_name", "唐花");
        ::setup();
}
