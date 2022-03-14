# ОТВЕТЫ НА ВОПРОСЫ ДЛЯ САМОПРОВЕРКИ

### 1) Какой ресурс называется критическим ресурсом?
*Критический ресурс* - ресурс, который доступен нескольким процессам.

### 2) Какой участок программы называется критическим участком?
*Критический участок* - участок программы процесса, в котором описаны действия с критическим ресурсом.

### 3) Какой режим выполнения программ называется режимом взаимного исключения?
*Режим взаимного исключения* - режим, при котором только один из процессов работает с критическим участком в один момент времени.

### 4) Перечислите способы организации режима взаимного исключения.
1. **Запрет прерываний**<br/>
У этого способа есть некоторые недостатки:
- закрываются *все* прерывания;
- приостанавливается выполнения всех процессов, кроме активного (даже тех, кто не собирался использовать ресурс).<br/>

Этот способ может быть использован только для коротких критических участков.

2. **Маскирование прерываний только от таймера**<br/>
Это более "тонкий" способ, он устраняет первый недостаток предыдущего, то есть система продолжает реагировать на любые внешние сигналы. Но второй недостаток этот метод не решает, процессы, не имеющие отношения к этому ресурсу, приостанавливаются.<br/>

3. **Использование флага занятости ресурса**<br/>
Процесс перед входом в критический участок проверяет значение флага. Если ресурс свободен, то процесс устанавливает флаг в состояние 1 и входит в критический участок, если ресурс занят, то процесс снова переходит на проверку значения флага. При выходе из критического участка процесс устанавливает флаг в состояние 0.<br/>
Этот способ имеет как достоинства, так и недостатки. К преимуществам можно отнести фиксированную и маленькую длину критического участка с флагом, недостатком же - способ не избавляет от "активного ожидания" - цикла опроса флага до его освобождения (один процесс может одновременно с другим проверять флаг и не получать доступ к желаемогому ресурсу).<br/>

4. **Семафоры**<br/>
*Семафор* - средство самой ОС, обеспечивающее режим взаимного исключения.<br/>
Идея способа состоит в том, что процессы, ожидающие доступа к ресурсу, делают это в очереди.<br/>
Можно различать двоичный и общий семафор Дейкстры.
*Двоичный семафор* содержит флаг, который свидетельствует о занятости или незанятости ресурса, и очередь, в которой находится процесс, если ресурс занят. *Общий семафор* вместо флага занятости ресурса содержит счетчик, содержимое которого позволяет оценить состояние семафора (позволяет обеспечить большее разнообращие правил нахождения потоков в критическом участке).<br/>
*Особенности семафора:*
- вставая в очередь семафора до освобождения ресурса, процесс разгружает процессор;
- на каждый ресурс нужен свой семафор, а значит, своя очередь, поэтому в ядре и много очередей;
- семафор - это тоже разделяемый ресурс, а значит, действия с ним должны выполняться в режиме взаимного исключения;
- использование семафора обеспечивает возможность безостановочной работы процессов, не требующих ресурсов.<br/>

Семафоры также  бывают *неименованные* и *именованные*. Неименованные семафоры используются для синхронизации потоков, именованные семафоры используются для синхронизации процессов.

5. **Мьютексы**<br/>
*Мьютекс* - средство ОС, принадлежащее библиотеке `PTHREAD`, обеспечивающее режим взаимного исключения.<br/>
Идея работы мьютекса аналогична идее работы двоичного семафора с одним отличием - у мьютекса есть владелец (поток, захвативший его). Если критический участок свободен, то поток захватывает мьютекс и входит в критический участок. При выходе из критического участка поток освобождает мьютекс. Если критический участок занят, то поток, при попытке захватить мьютекс, блокируется и не входит в критический участок. Активизация заблокированного потока и вход в критический участок происходит тогда, когда ранее вошедший в критический участок поток выходит из него и освобождает мьютекс.

### 5) Опишите алгоритмы операций захвата и освобождения мьютекса.
В начале работы программы мьютекс необходимо создать:
```c
    int pthread_mutex_init(pthread_mutex_t *mutex, const pthread_mutexattr_t *attr);
```
Здесь:
- `mutex` - идентификатор потока;
- `attr` - указатель на структуру данных, описывающих атрибуты мьютекса.<br/>

**Средство имеет две операции:**<br/>
- `pthread_mutex_lock(pthread_mutex_t *mutex)` - вход в критический участок;
- `pthread_mutex_unlock(pthread_mutex_t *mutex)` - выход из критического участка.<br/>

Исходно ресурс свободен. Поток, который первым подошел к критическому участку, захватывает мьютекс и входит в критический участок. Второй поток, когда вызывает операцию `pthread_mutex_lock()` над захваченным мьютексом, блокируется и не может войти в критический участок. Когда первый поток выходит из критического участка, он вызывает операцию `pthread_mutex_unlock()` и освобождает мьютекс. Тем самым позволяет захватить мьютек второму потоку и войти в критический участок.<br/>

В конце работы программы мьютекс надо удалить:
```c
   int pthread_mutex_destroy(pthread_mutex_t *mutex);
```

### 6) Опишите алгоритмы операций захвата и освобождения семафора.
Создание неименованного семафора производится вызовом:
```c
    int sem_init(sem_t *sem, int shared, unsigned int value);
```
Здесь:
- `sem` - идентификатор семафора;
- `shared` - индикатор использования семафора потоками и процессами (неименованные семафоры также могут быть использованы для синхранизации процессов: если процессы связаны отношением родитель-потомок и если семафор помещен в разделяемую память);
- `value` - начальное значение счетчика семафора.<br/>

**Средство имеет две операции:**<br/>
- `sem_wait(sem_t *sem)` - вход в критический участок;
- `sem_post(sem_t *sem)` - выход из критического участка.<br>

Если один поток прошел через свою операцию `sem_wait()` и вошел в критический участок, то второй поток, вызывая функцию `sem_wait()`, будет приостановлен до тех пор, пока первый поток не выйдет из критического участка и не вызовет операцию `sem_post()`.<br/>

Удаление семафора производится вызовом:
```c
    int sem_destroy(sem_t *sem);
```

### 7) Какими операциями с мьютексом и с неименованным семафором можно осуществить проверку занятости ресурса без блокирования потока?
**Для решения этой задачи для мьютексов определены следующие функции (если ресурс свободен, функции работают аналогично** `pthread_mutex_lock()`**):**
```c
    int pthread_mutex_trylock(pthread_mutex_t *mutex);
```
Если ресурс занят, то функция не блокируется в ожидании освобождения ресурса, а сразу же возвращает управление с кодом ошибки `EBUSY`. В этом случае нужно сделать небольшую задержку и снова вызвать эту функцию. Получается некоторое подобие опроса состояния ресурса. Чем меньше будет задержка, тем точнее определится момент освобождения ресурса.<br/>
Опасность использования этой функции состоит в том, что между моментами опроса ресурс может быть освобожден или снова захвачен.
```c
    int pthread_mutex_timedlock(pthread_mutex_t *mutex, const struct timespec *abs_timeout);
```
Если ресурс занят, то функция блокируется до времени `abs_timeout` в ожидании освобождения ресурса. Если в течение времени ожидания ресурс не освободится, функция завершается с кодом ошибки `ETIMEDOUT`. В этом случае надо просто снова вызвать функцию, так как она сама реализует задержку. И она снова будет ждать освобождения ресурса установленное время.<br/>
Важной особенностью функции `pthread_mutex_timedlock` является использование *абсолютного* времени, то есть перед вызовом данной функции необходимо получить текущее время, прибавить к нему требуемое время ожидания и передать это время в функцию.<br/>
Для получения текущего времени можно использовать функцию `int clock_gettime(clockid_t clk_id, struct timespec *tp)`, где `clockid_t clk_id` - тип часов, а время задается структурой `timespec`<br/><br/>
**Для семафоров определены следующие функции (если ресурс свободен, функции работают аналогично** `sem_wait()`**):**
```c
    int sem_trywait(sem_t *sem);
```
Если ресурс занят, то функция не блокируется в ожидании освобождения ресурса, а сразу же возвращает управление с кодом ошибки -1 и устанавливает errno в `EAGAIN`.
```c
    int sem_timedwait(sem_t *sem, const struct timespec *abs_timeout);
```
Если ресурс занят, то функция блокируется в ожидании освобождения ресурса до времени `abs_timeout`, если в течение этого времени ресурс не освободится, функция возвращает управление с кодом ошибки -1 и устанавливает errno в `ETIMEOUT`. Время ожидания устанавливается аналогично предыдущему варианту.