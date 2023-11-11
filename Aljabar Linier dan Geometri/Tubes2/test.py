# import cv2
# import numpy as np

# def cosine_similarity(v1, v2):
#     dot_prod = np.dot(v1, v2)
#     norm_v1 = np.linalg.norm(v1)
#     norm_v2 = np.linalg.norm(v2)
#     if norm_v1 == 0 or norm_v2 == 0:
#         return 0
#     else:
#         return dot_prod / (norm_v1 * norm_v2)

# # Load the first image and calculate its HSV histogram
# image1 = cv2.imread('waifu2.jpeg')
# hsv_image1 = cv2.cvtColor(image1, cv2.COLOR_BGR2HSV)
# hist_hue1 = cv2.calcHist([hsv_image1], [0], None, [8], [0, 360])
# hist_saturation1 = cv2.calcHist([hsv_image1], [1], None, [3], [0, 100])
# hist_value1 = cv2.calcHist([hsv_image1], [2], None, [3], [0, 100])

# # Load the second image and calculate its HSV histogram
# image2 = cv2.imread('948.jpg')
# hsv_image2 = cv2.cvtColor(image2, cv2.COLOR_BGR2HSV)
# hist_hue2 = cv2.calcHist([hsv_image2], [0], None, [8], [0, 360])
# hist_saturation2 = cv2.calcHist([hsv_image2], [1], None, [3], [0, 100])
# hist_value2 = cv2.calcHist([hsv_image2], [2], None, [3], [0, 100])

# # Concatenate the histograms into a single vector
# hist_concatenated1 = np.concatenate((hist_hue1, hist_saturation1, hist_value1)).flatten()
# hist_concatenated2 = np.concatenate((hist_hue2, hist_saturation2, hist_value2)).flatten()

# # Calculate cosine similarity
# cosine_similarity_value = cosine_similarity(hist_concatenated1, hist_concatenated2)

# print("Cosine Similarity:", cosine_similarity_value*100)

# bhattacharyya_distance = cv2.compareHist(hist_concatenated1, hist_concatenated2, cv2.HISTCMP_BHATTACHARYYA)

# print("Bhattacharyya Distance:", bhattacharyya_distance*100)


# import cv2
# import numpy as np

# def calculate_hsv_histogram(image, h_bins, s_bins, v_bins):
#     hsv_image = cv2.cvtColor(image, cv2.COLOR_BGR2HSV)
#     h_hist = cv2.calcHist([hsv_image], [0], None, h_bins, [0, 256])
#     s_hist = cv2.calcHist([hsv_image], [1], None, s_bins, [0, 256])
#     v_hist = cv2.calcHist([hsv_image], [2], None, v_bins, [0, 256])
#     hist = np.concatenate((h_hist, s_hist, v_hist), axis=None)
#     return hist

# def compare_histograms(hist1, hist2):
#     return cv2.compareHist(hist1, hist2, cv2.HISTCMP_CORREL)

# if __name__ == "__main__":
#     # Load your two images
#     image1 = cv2.imread("948.jpg")
#     image2 = cv2.imread("waifu2.jpeg")

#     # Calculate histograms for both images
#     h_bins = [8]  # Adjust the number of bins according to your requirements
#     s_bins = [3]
#     v_bins = [3]
    
#     hist1 = calculate_hsv_histogram(image1, h_bins, s_bins, v_bins)
#     hist2 = calculate_hsv_histogram(image2, h_bins, s_bins, v_bins)

#     # Compare the histograms
#     correlation = compare_histograms(hist1, hist2)

#     print("Histogram Correlation:", correlation)

# def create_histogram_downsample(hsv_matrix):
#     mod3_width = (hsv_matrix.shape[1] // 3) * 3
#     mod3_length = (hsv_matrix.shape[0] // 3) * 3

#     mod3_hsv_matrix = hsv_matrix[:mod3_length,:mod3_width]

#     reshaped_matrix = mod3_hsv_matrix.reshape(hsv_matrix.shape[0] // 3, 3, hsv_matrix.shape[1] // 3, 3, 3)
#     downsampled_matrix = np.mean(reshaped_matrix, axis=(1, 3))
#     h_channel = downsampled_matrix[:, :, 0]
#     s_channel = downsampled_matrix[:, :, 1]
#     v_channel = downsampled_matrix[:, :, 2]

#     h_bins = [0, 25, 40, 120, 190, 270, 295, 315, 361]
#     s_bins = [0, 0.2, 0.7, 1]
#     v_bins = [0, 0.2, 0.7, 1]

#     hist_h, bin_edges_h = np.histogram(h_channel, bins=h_bins)
#     hist_s, bin_edges_s = np.histogram(s_channel, bins=s_bins)
#     hist_v, bin_edges_v = np.histogram(v_channel, bins=v_bins)

#     concat = np.concatenate((hist_h, hist_s, hist_v))

#     return concat

# def create_histogram(hsv_matrix):
#     h_channel = hsv_matrix[:, :, 0]
#     s_channel = hsv_matrix[:, :, 1]
#     v_channel = hsv_matrix[:, :, 2]

#     h_bins = [0, 25, 40, 120, 190, 270, 295, 315, 361]
#     s_bins = [0, 0.2, 0.7, 1]
#     v_bins = [0, 0.2, 0.7, 1]

#     hist_h, bin_edges_h = np.histogram(h_channel, bins=h_bins)
#     hist_s, bin_edges_s = np.histogram(s_channel, bins=s_bins)
#     hist_v, bin_edges_v = np.histogram(v_channel, bins=v_bins)

#     concat = np.concatenate((hist_h, hist_s, hist_v))

#     return concat


import cv2
import numpy as np
from sklearn.metrics.pairwise import cosine_similarity

# Load the reference image
image1 = cv2.imread('948.jpg')

# Load the image to compare with
image2 = cv2.imread('waifu2.jpeg')

# Convert both images to HSV color space
hsv_image1 = cv2.cvtColor(image1, cv2.COLOR_BGR2HSV)
hsv_image2 = cv2.cvtColor(image2, cv2.COLOR_BGR2HSV)

print("max img1: ", np.max(hsv_image1))

# Calculate histograms for both images
hist_hue1 = cv2.calcHist([hsv_image1], [0], None, [8], [0, 180])
hist_saturation1 = cv2.calcHist([hsv_image1], [1], None, [3], [0, 256])
hist_value1 = cv2.calcHist([hsv_image1], [2], None, [3], [0, 256])

hist_hue2 = cv2.calcHist([hsv_image2], [0], None, [8], [0, 180])
hist_saturation2 = cv2.calcHist([hsv_image2], [1], None, [3], [0, 256])
hist_value2 = cv2.calcHist([hsv_image2], [2], None, [3], [0, 256])

# Concatenate the histograms into a single vector
hist_combined1 = np.concatenate((hist_hue1, hist_saturation1, hist_value1))
hist_combined2 = np.concatenate((hist_hue2, hist_saturation2, hist_value2))

# Reshape the histograms to have a shape of (1, -1) for cosine similarity calculation
hist_combined1 = hist_combined1.reshape(1, -1)
hist_combined2 = hist_combined2.reshape(1, -1)

# Calculate cosine similarity between the two histograms
cosine_sim = cosine_similarity(hist_combined1, hist_combined2)

# Cosine similarity ranges from -1 (completely dissimilar) to 1 (completely similar)
print(f"Cosine Similarity: {cosine_sim[0][0]}")
