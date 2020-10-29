// zhen.c
// by Find.

#undef TEST

/*
zhen ji 建立
zhen yq 邀请
zhen in 加入
zhen huan 换阵主
zhen san 解散阵法
zhen talk 阵法说话
zhen check 阵主察看成员的状态
*/

inherit F_CLEAN_UP;
protected void select_array(string arg,object me,string *ski);
protected void build_up(object me,string fn);

nomask int main(object me, string arg)
{
        string usr,*ski,*z_ski = ({});
        int i,n;

#ifdef TEST
        if(!wizardp(me))
                return notify_fail("测试期间只有巫师能使用阵法。\n");
#endif

        if(!stringp(arg) || arg =="")
        {
                if(!me->in_array())
                        return notify_fail("你目前没有加入任何阵法。\n");
        // 等级 15 级
        // 救援及时、防御等级高、阵法攻击效果好
                else
                {
                        object *memb;
                        string out;
                        object w;
        
                        if( (w = me->query_array_master()) == me)
                                out = sprintf("你目前正在主持『%s』\n",me->query_array_name());
                        else
                                out = sprintf("你目前正在%s主持的『%s』中\n",w->name(),me->query_array_name());
        
                        memb = me->query_array_member() - ({ me,0 });
        
                        if(!sizeof(memb))
                                out += "阵形中没有其他成员。\n";
                        else
                        {
                                out += "成员有：\n";
                                foreach(object cy in memb)
                                        out += sprintf("\t%s\n",cy->name());
                                out += sprintf("\t%s\n",me->name());
                        }

                        out += sprintf("『%s』%s。\n",
                        me->query_array_name(),
                        me->query_array_status()?
                                sprintf("正在发挥威力\n阵法等级为：%d",me->query_array_level()):
                                "的威力还没有发挥出来");
                        write(out);
                        return 1;
                }
        }

        if(arg[0..4] == "check")
        {
                object who;

                if(!me->in_array())
                        return notify_fail("你目前没有加入任何阵法。\n");

                if(!me->is_array_master())
                        return notify_fail("只有阵主才能查看成员的状态。\n");

                if( !sscanf(arg,"check %s",usr)
                || !objectp(who = present(usr,environment(me)))
                || !userp(who) )
                        return notify_fail("你要查看哪个成员的状态？\n");
                if(!me->is_array_member(who))
                        return notify_fail(sprintf("%s不是『%s』的成员。\n",
                                who->name(),me->query_array_name() ));

                write(sprintf("『%s』%s%s：\n\t当前使用武功为：%s\n\t『%s』的等级为：%d\n\t『%s』等级为：%d\n",
                        who->query_array_name(),
                        who == me?"阵主":"成员",
                        who->name(),
                        to_chinese(who->query_current_skill()),
                        who->query_array_name(),
                        who->query_skill((who->query_array_fn())->query_array_id(),1),
                        to_chinese((who->query_array_fn())->query_array_skill()),
                        who->query_skill((who->query_array_fn())->query_array_skill(),1)
                        ));

                return 1;
        }

        if(arg == "ji")        // 建立
        {
                string out;

                if(me->is_fighting())
                        return notify_fail("你正在和人打架，顾不上其它的事情。\n");

                if(me->in_team())
                        return notify_fail("你正在队伍中，无法组织阵法。\n");

                if(me->in_array()) // xx带领的xx
                {
                        if(me->query_array_master() == me)
                                return notify_fail(sprintf("你现在正在主持『%s』。\n",
                                me->query_array_name()));
                        else
                                return notify_fail(sprintf("你已经是%s带领的『%s』的成员了。\n",
                                        me->query_array_master()->name(),
                                        me->query_array_name()));
                }

                if(!(ski = me->query_skills_name()) || !(n = sizeof(ski)))
                        return notify_fail("你什么阵法都不会。\n");
                
                for(i=0;i<n;i++)
                {
                        string s;
                        if(stringp(s=SKILL_D(ski[i])) && s->is_array_skill())
                                z_ski += ({ s });
                }
                
                if(!n = sizeof(z_ski))
                        return notify_fail("你什么阵法都不会。\n");
                if(n == 1)
                {
                        build_up(me,z_ski[0]);
                        return 1;
                }
                
                out = "你目前掌握的阵法有：\n";
                for(i=0;i<n;i++)
                        out += sprintf("\t%d. 『%s』\n",(i+1),z_ski[i]->query_name());
                out += "请选择你要组建的阵法：(q退出)";
                write(out);
                input_to((: select_array :),me,z_ski);
                return 1;
        }

        if(arg == "san")
                return me->release_array(0);

        if(arg[0..1] == "yq")
        {
                object who;

                if(!me->in_array())
                        return notify_fail("你目前没有加入任何阵法。\n");

                if(!me->is_array_master())
                        return notify_fail("只有阵主才能邀请别人入阵。\n");

                if(me->is_fighting())
                        return notify_fail("你正在和人打架，顾不上其它的事情。\n");

                if( !sscanf(arg,"yq %s",usr)
                || !objectp(who = present(usr,environment(me)))
                || !userp(who)
                || (who == me) )
                        return notify_fail("你要邀请谁入阵？\n");

                if(me->is_array_member(who))        // already in
                        return notify_fail(sprintf("%s已经在你主持的『%s』中了。\n",
                                who->name(),me->query_array_name()));

#ifdef TEST
                if(userp(who) && !wizardp(who))
                        return notify_fail("测试期间你只能邀请巫师入阵。\n");
#else
                if(wizardp(who))
                        return notify_fail("你不能邀请巫师入阵。\n");
#endif

                if(who->in_team())
                        return notify_fail("对方正在其它的队伍中，无法加入你的阵法。\n");

                if(!me->can_become_member(who))
                        return 0;

                tell_object(who,sprintf("%s邀请你加入%s主持的『%s』。\n",
                        me->name(),
                        gender_pronoun(query("gender", me)),
                        me->query_array_name() ));

                tell_object(me,sprintf("你邀请%s加入你主持的。\n",
                        who->name(),me->query_array_name()));

                set_temp("pending/team", me, who);
                return 1;
        }

        if(arg == "in")
        {
                object who=query_temp("pending/team", me);

                if(!objectp(who))
                        return notify_fail("你并没有被任何人邀请加入阵法。\n");

                if(me->in_team())
                        return notify_fail("你正在队伍中，无法加入其它的阵法。\n");

                if(environment(who) != environment(me))
                        return notify_fail(sprintf("%s已经走了。\n",who->name()));

                if(me->in_array())
                {
                        if(me->query_array_master() == me)
                                return notify_fail(sprintf("你正在主持『%s』,无法加入其它的阵法。\n",
                                        me->query_array_name()));
                        else
                                return notify_fail(sprintf("你正在%s主持的『%s』中,无法加入其它的阵法。\n",
                                        me->query_array_master()->name(),
                                        me->query_array_name()));
                }

                if(!who->add_array_member(me))
                        return 0;

                tell_object(me,sprintf("你应邀加入%s主持的『%s』。\n",
                        who->name(),who->query_array_name() ));
                return 1;
        }

        if(arg[0..3] == "talk")
        {
                string msg;
                object *memb;

                if(!me->in_array())
                        return notify_fail("你没有在任何阵法之中。\n");

                if(sizeof(memb = me->query_array_member()) < 2)
                        return notify_fail(sprintf("『%s』中目前还没有其他成员。\n",
                                me->query_array_name()));

                if(!sscanf(arg,"talk %s",msg))
                        msg = "。。。\n";

                if(msg[<1] != '\n')
                        msg += "\n";

                message("tell_object",sprintf("【%s】%s(%s)：%s",
                        me->query_array_name(),
                        me->name(),
                        capitalize(query("id", me)),
                        msg ), memb);
                return 1;
        }
        write("请 help zhen 获得此命令使用方法的帮助。\n");
        return 1;
}

protected void select_array(string arg,object me,string *ski)
{
        int n,size;

        if(!stringp(arg)
        || (arg == "")
        || !me
        || !arrayp(ski)
        || !(size = sizeof(ski)))
                return;

        if( (arg[0] == 'q')
        || (arg[0] == 'Q') )
        {
                tell_object(me,"ok.\n");
                return;
        }

        if(!sscanf("%d",n))
        {
                tell_object(me,"\n请选择你要组建的阵法：(q退出)");
                input_to((: select_array :),me,ski);
                return;
        }

        n--;

        if( (n < 0) || (n >= size) )
        {
                tell_object(me,"\n请选择你要组建的阵法：(q退出)");
                input_to((: select_array :),me,ski);
                return;
        }

        build_up(me,ski[n]);
        return;
}

protected void build_up(object me,string fn)
{
        if(!me
        || !stringp(fn)
        || (file_size(fn+".c") <= 0) )
                return;

        if(!fn->valid_build(me))
                return;

        if(!me->build_up_array(fn))
                return;

        message_vision(sprintf("$N开始组织『%s』。\n",me->query_array_name()),me);
}

int help(object me)
{
   write( @HELP

阵法操作命令，使用方法如下：

zhen ji
        开始组建一个你所会的阵法，如果你要是会
        多个阵法，会自动让你选择想要组建的阵法。
        此命令可以简写为： zj

zhen yq <ID>
        邀请别人加入你开始组建的阵法，<ID> 是你
        要邀请人的 ID，当然此人要符合运转此阵法
        的基本条件。
        此命令可以简写为： zyq <ID>

zhen in
        如果你受到了别人的邀请，如果愿意的话，可
        以用这个命令加入阵形。
        此命令可以简写为： zin

zhen san
        解散目前正在运用的阵法。解散命令只能由阵
        主发出。
        此命令可以简写为： zs

zhen talk
        已经组建的阵法成员之间可以用这个命令对话。
        此命令可以简写为： zt

zhen check <ID>
        阵主可以用这个命令检查当前阵法成员的一些状
        态，如：成员当前所使用的武功，此阵法的等级，
        阵法所要求的武功的等级。。。<ID>为要检查成
        员的 ID。
        此命令可以简写为： zck <ID>

zhen
        不加任何参数的 zhen 命令可以显示你当前所在
        阵形的一些状态，如：阵主是谁，都有哪些成员，
        是否开始发挥威力，你们所组成的阵法的有效等
        级是多少。。。

关于阵法的详细的帮助信息可 help zhenfa 查看。

HELP
   );
   return 1;
}
