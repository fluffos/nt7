inherit F_CLEAN_UP;
#include <ansi.h>

mixed random_gift();

nosave mixed *story = ({
        "某人走在丛林中，忽然间一头野猪向你冲了过来……",
        "某人搭弓就是一箭，野猪应声而倒… 某人将野猪皮毛清理干净，便生起一堆火来……",
        "一柱香后……",
        "赏善使：“哇！真香啊！”",
        "罚恶使：是啊！走，咱们过去瞧瞧。",
        "某人一边烤着野猪肉，一边享受着从肉中散发出来的香味。",
        "这时只见两个人走了过来，其中一人说道：“这肉真香啊！”",
        "某人连忙说道：“二位若不嫌弃，就一同吃吧！反正这么大一块我一个人也吃不完。”",
        "赏善使：“阁下真是心地善良，二弟咱们就吃吧！”",
        "罚恶使：“好，来大哥把咱们酒拿出来喝吧……”",
        "某人说道：“二位英雄你们这酒我能喝吗？”",
        "赏善使：“这酒不是普通的酒，内力不济之人喝了轻则伤身，重则性命不保！我劝你还是不要喝得好。”",
        "罚恶使：“对，不要喝得好！”",
        "某人实在可渴得厉害，拿起两个酒葫芦便喝了起来……",
        "赏善使：“？？？”",
        "罚恶使：“！！！”",
        "不一会儿，某人感觉体内有两股真气在不断相冲，赶忙运功化解……",
        (: random_gift :),
});

void create()
{
        seteuid(getuid());
}

string prompt() { return HIR "【奇遇】" NOR; }

mixed query_story_message(int step)
{
        return step < sizeof(story) ? story[step] : 0;
}

mixed random_gift()
{
        object *obs;
        object ob;
        string msg;
        int max_neili;

        obs = filter_array(all_interactive(), (: ! wizardp($1) &&
                                                 environment($1) &&
                                                 query("outdoors", environment($1)) && 
                                                 !query("env/no_story", $1) && 
                                                 !query("doing", $1):));
        if (! sizeof(obs))
                return 0;

        ob = obs[random(sizeof(obs))];
       
        if( query("gift/max_neili", ob) || random(5 )
             || query("character", ob) != "光明磊落"
             || query("max_neili", ob)<3000 )
        {
                msg = HIR + ob->name(1) + "一声惨叫，昏了过去。" NOR;
                ob->unconcious();
        } else
        {
                msg = HIY "过了良久" + ob->name(1) +
                      HIY "运功完毕，只觉得神清气爽，内力大增。" NOR;
                ob->improve_neili(100000);
                set("gift/max_neili", 1, ob);
        }
        return msg;
}
