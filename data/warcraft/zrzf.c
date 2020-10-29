// warcraft.c

#include "/clone/npc/warcraft.h"

void setup()
{
        set_name("[1;37m大[1;37m[1;35m冢[1;35m[2;37;0m[2;37;0m", ({"dazhong"}));        
        set("gender", "女性");                
        set("long", "AV女王[2;37;0m
它是粽唐的魔幻兽。
");
        set("race_type", "白虎");
        set("magic/type", "metal");
        set("owner", "zrzf");
        set("owner_name", "粽唐");
        set_temp("owner", "zrzf");
        set_temp("owner_name", "粽唐");
        ::setup();
}
