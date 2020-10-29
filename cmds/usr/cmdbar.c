int main(object me,string arg)
{
        //Look  score  hp  search  say   chat  chann  I   fee  who  map  help  alias  icon  
        string *cmdbar;
        string *tmp = ({
                "观察=look","物品=i","评价ＳＣ=score","状态ＨＰ=hp",
                "功夫ＳＫ=cha","设置头像=face ...","查询费用=fee",
                "设置频道=chann","搜索=search","在线=who",
                "帮助=help ...","说话=say ...","闲聊=chat ...",});

        
        cmdbar=query("cmdbar", me);
        if(!arrayp ( cmdbar ) || sizeof(cmdbar)!=13)
                cmdbar = tmp;
        //me->set("cmdbar",cmdbar);//以后如果受玩家欢迎的话可以允许他们自己定义命令（关闭重新运行后生效）
        write(TMI("cmdbar "+implode(cmdbar,";")+";"));
        return 1;
}