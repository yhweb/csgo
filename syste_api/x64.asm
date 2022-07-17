.code 
;x64环境下编译汇编指令    生成依赖项 自定义 masm 
;排除x64代码关联到项目中  x64.asm 属性 从生成中排除 且 项类型 文本
;添加新建项 后缀 .asm
;不能用//注释
;call名 proc 开始
mycall proc
;数据交个RAX 并返回
mov rax,1111122h
ret 
;endp 表示结束
mycall endp


myadd proc
mov rax,2222h
ret
myadd endp

end
