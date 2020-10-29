// story:donghai 东海龙传说

#include <ansi.h>

int give_gift(string name);

nosave mixed *story = ({
        "哪吒：我洗澡去了。",
        "李天王：去就去，可少给我惹事。",
        "......",
        "哪吒：洗洗头！",
        "哪吒：冲冲脚！",
        "哪吒：待我搓搓背！恩？我的小布条呢...",
        "唏～哩～哗～啦～～～",
        "东海龙王：我的天，怎么晃得这么厉害？",
        "虾兵蟹将：呼噜呼噜，不得了了！",
        "龙子龙孙：喔喔，老爸救命啊！",
        "三太子：岂有此理！一定是有人搞破坏，待我去查个明白！",
        "龙妹妹：哇，好帅呀！",
        "......",
        "三太子：兀那小子，东海龙宫岂是你折腾的地方？",
        "哪吒：什么人，打扰我洗澡？赏你一铁圈！",
        "啪！",
        "噢呦！",
        (: give_gift, "donghai" :),
        "听说三太子(prince of dragon)和哪吒发生冲突，被打落凡间。",
});

string prompt() { return HIM "【神话】" NOR; }

void create()
{
        seteuid(getuid());
}

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

int give_gift(string name)
{
        object ob;

        ob = new(CLASS_D("misc/") + name);
        if (! objectp(ob))
                return 0;

        NPC_D->place_npc(ob);
        if (! objectp(environment(ob)))
        {
                destruct(ob);
                return 0;
        }

        CHANNEL_D->do_channel(find_object(STORY_D), "sys",
                              ob->name() + "出现在" + environment(ob)->short() +
                              "(" + base_name(environment(ob)) + ")。");
        return 1;
}
