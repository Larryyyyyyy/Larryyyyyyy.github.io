const audioList = [
      './static/audio/sasakure.UK - uzumakinoharu.mp3',
      './static/audio/t+pazolite - Squeaky Mind.mp3',
      './static/audio/ak+q - astrum.mp3',
      './static/audio/ak+q - variations on a soul.mp3',
      './static/audio/Loadstar-M2U.NICODE.mp3',
      './static/audio/Altale-Sakuzyo.mp3',
      './static/audio/Cre-sc3NT & 橙沁Asa - Seeking Twilight.mp3',
      './static/audio/sasakure.UK - …to mo da ti _.mp3',
      './static/audio/AcuticNotes - 存在信号 (Aw.0000).mp3',
      './static/audio/ak+q - white.roses.mp3',
      './static/audio/眠りの吸血鬼-流派未確定.mp3',
      './static/audio/Feryquitous & t+pazolite - Callima Karma.mp3',
      './static/audio/Feryquitous - Maquitous -八戒-.mp3',
      './static/audio/削除 - Dead.mp3',
      './static/audio/凋叶棕 - 未だ知られぬ物語 ～ Anticipated Dream.mp3',
      './static/audio/ELECTROCUTICA - Me.mp3',
      './static/audio/sasakure.UK - 回ル想ヒ.mp3'
    ];
    let currentIndex = 0;
    const audioElement = document.getElementById('audio');
    const playPauseBtn = document.getElementById('playPauseBtn');
    const currentSong = document.getElementById('currentSong');
    const previousBtn = document.getElementById('previousBtn');
    const nextBtn = document.getElementById('nextBtn');
    const player = document.getElementById('audioPlayer');
    const progressBar = document.getElementById('progressBar');
	progressBar.style.width = '20%';
    const progressBar_volume = document.getElementById('progressBar_volume');
	progressBar_volume.style.width = '20%';
	  const volume_img = document.getElementById('volume_img');

    // 设置音量
    function setVolume(volume) {
      audioElement.volume = volume;
	  if (volume>=0.50) volume_img.src="static/img/volume-up.svg";
	  if (volume>0&&volume<0.50) volume_img.src="static/img/volume-down.svg";
	  if (volume==0) volume_img.src="static/img/volume-mute.svg";
    }

    // 播放/暂停音频
    function togglePlayPause() {
      if (audioElement.paused) {
        audioElement.play();
        playPauseBtn.innerHTML = '<i class="fas fa-pause"></i>';
      } else {
        audioElement.pause();
        playPauseBtn.innerHTML = '<i class="fas fa-play"></i>';
      }
    }

    // 播放下一首音频
    function playNext() {
      currentIndex = (currentIndex + 1) % audioList.length;
      audioElement.src = audioList[currentIndex];
      audioElement.play();
      playPauseBtn.innerHTML = '<i class="fas fa-pause"></i>';
      currentSong.innerText = `${audioList[currentIndex].split('/').pop()}`;
    }

    // 播放上一首音频
    function playPrevious() {
      currentIndex = (currentIndex - 1 + audioList.length) % audioList.length;
      audioElement.src = audioList[currentIndex];
      audioElement.play();
      playPauseBtn.innerHTML = '<i class="fas fa-pause"></i>';
      currentSong.innerText = `${audioList[currentIndex].split('/').pop()}`;
    }

    // 监听音频播放完毕事件
    audioElement.onended = function () {
      playNext();
    };

    // 控制按钮事件绑定
    playPauseBtn.addEventListener('click', togglePlayPause);
    previousBtn.addEventListener('click', playPrevious);
    nextBtn.addEventListener('click', playNext);

    // 设置初始音量
    setVolume(0.5);

    // 鼠标移动到底部显示播放器
    document.body.addEventListener('mousemove', function (event) {
      if (event.clientY > window.innerHeight - 110) {
        player.classList.add('active');
      } else {
        player.classList.remove('active');
      }
    });
	
	// 更新进度条显示
    audioElement.addEventListener('timeupdate', () => {
      const progress = (audioElement.currentTime / audioElement.duration) * 100;
      progressBar.value = progress; // 更新进度条值
    });
	
    // 拖动进度条控制播放位置
    progressBar.addEventListener('input', () => {
      const newTime = (progressBar.value / 100) * audioElement.duration;
      audioElement.currentTime = newTime; // 设置音频播放时间
    });