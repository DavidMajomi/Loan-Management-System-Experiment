var isMobile = /Android|webOS|iPhone|iPad|iPod|BlackBerry|IEMobile|Opera Mini/i.test(navigator.userAgent);


var backgroundContainer = document.getElementById('background-image');
var customButton = document.getElementById('custom-button');
var testPhoneContent = document.getElementById('content-section');


// Apply mobile background class if the user is on a mobile device
if (isMobile) {
    backgroundContainer.classList.add('mobile-background');
    customButton.classList.add('mobile-custom-button');
    testPhoneContent.classList.add('mobile-content-section');
}