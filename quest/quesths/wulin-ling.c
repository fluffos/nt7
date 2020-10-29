inherit ITEM;

void create()
{
        set_name( "武林令", ({ "wulin ling", "ling"}) );
        set_weight(100);
        if( clonep() )
                set_default_object(__FILE__);
        else {
                set("unit", "块");
                set("long", "这是一块武林同盟使用的铁令，见令如见盟主。 由黄裳签发，处理武林同盟一应事务。\n");
                set("value", 0);
                set("material", "iron");
        }
        setup();
}

void init()
{
        add_action("do_chushi","chushi");
}

int do_chushi(string arg)
{
        object thing,obj,me,who;
        mapping quest;
        me = this_player();
        if( !quest=query("quest_hs", me) )
            return notify_fail("你没有接到征收的任务，在这里用英雄令晃啊晃的干啥？\n");
        if (!arg) return notify_fail("你要向谁出示武林令？");
        if (! objectp(who = present(arg, environment(me))))
            return notify_fail("这里没有这个人。\n");
        if( query_temp("quester", who) != query("id", me) || quest["target"] != query("id", who) )
            return notify_fail("你不要仗着武林同盟的名声到处招摇撞骗！\n");
        message_vision("$N高举武林令，对着$n大声说：“你这个家伙，准备躲着武林盟主多久？\n"
                       "好在今天让我找到了你！黄大人让我来收取"+quest["name"]+"，你就乖乖的交出来吧！\n",me,who);
        message_vision("$N见到$n手中的武林令，不由一声长叹：“躲了这么久，还是给你们找到了，也罢也罢！\n"
                       "你要的东西我这里有，就交给你了。\n",who,me);
        thing = new(quest["object"]);
        set_temp("zheng",query("id",  me), thing);
        if (!thing->move(me))
        {
                thing->move(environment(me));
            message_vision("$N将"+thing->name(1)+"放在地上。\n",who);
        }
        else
            message_vision("$N将"+thing->name(1)+"交给了$n。\n",who,me);

        message_vision("$N挥了挥手，转身离开了。\n",who);
        destruct(who);
        return 1;
}
            
     